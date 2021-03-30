#!/bin/bash

YELLOW="\033[1;33m"
RED="\033[1;31m"
GREEN="\033[1;32m"
BLUE="\034[1;32m"
OTHER="\033[5;36m"
WHITE="\033[0m"

if [ $# -ne 2 ]; then
    echo -e "$RED Wrong number of arguments $WHITE"
    exit 1
fi

FILE=$1
if [ -f $FILE ]
then
  clear
  echo -e "$GREEN =============================================================================================== \n"
  echo -e "$OTHER                     ██████╗ ███╗   ███╗██╗ ██████╗██╗  ██╗███████╗ █████╗ ██╗"
  echo -e "                     ██╔══██╗████╗ ████║██║██╔════╝██║  ██║██╔════╝██╔══██╗██║"
  echo -e "                     ██████╔╝██╔████╔██║██║██║     ███████║█████╗  ███████║██║"
  echo -e "                     ██╔══██╗██║╚██╔╝██║██║██║     ██╔══██║██╔══╝  ██╔══██║██║"
  echo -e "                     ██████╔╝██║ ╚═╝ ██║██║╚██████╗██║  ██║███████╗██║  ██║███████╗"
  echo -e "                     ╚═════╝ ╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ \n $WHITE"
  echo -e "$GREEN =============================================================================================== $WHITE\n"

  if grep -q "ft::$2" $FILE                                                    # заменяем первоначальное значение на второе
  then
    clang++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address $FILE && ./a.out > my_out
    clang++ $FILE -o valgrind_check

    echo -e "● clang++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address $FILE\n"
    echo -e "$GREEN =============================================================================================== $WHITE\n"
    sed -i '' 's/[a-zA-Z]*::'$2'/std::'$2'/g' $FILE
    echo -e "● change to $GREEN std:: $WHITE namespace \n"
    echo -e "$GREEN =============================================================================================== $WHITE\n"
    clang++ $FILE && ./a.out > std_out

#============================ DIFF =============================================
    diff my_out std_out > logs.txt
        ret=$?
        if [[ $ret -eq 0 ]]; then
            echo -e "$GREEN                                  NO differences! Well Done $WHITE ✅ \n "
            echo -e "$GREEN =============================================================================================== $WHITE\n"
            rm logs.txt

            valgrind ./valgrind_check > valgrind_log.txt
           #valgrind ./a.out > valgrind_log.txt #standart valgrind
           echo -e "$GREEN =============================================================================================== $WHITE\n"
        else
            echo -e "\n $RED ❌ ❌ ❌  Test Failed ❌ ❌ ❌ \n Open logs.txt for more details.$WHITE\n"
            exit 1
        fi

# ======================== BACK & remove trash =================================
        sed -i '' 's/[a-zA-Z]*::'$2'/ft::'$2'/g' $FILE                         # обратный реверс к первоначальному состоянию
        echo -e "● change back to $GREEN ft:: $WHITE namespace \n"
        rm a.out my_out std_out valgrind_check valgrind_log.txt
    echo -e "$GREEN =============================================================================================== $WHITE\n"
# ============================= IF STD =========================================
  elif grep -q "std::$2" $FILE
  then
    sed -i '' 's/[a-zA-Z]*::'$2'/ft::'$2'/g' $FILE
    echo -e "● $WHITE change back to $GREEN ft:: $WHITE namespace \n"

  fi # end of main grep block

# ============================= IF NO FILE =====================================
else
  echo -e "$RED $FILE doesn't exist $WHITE"
fi