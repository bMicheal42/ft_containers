#!/bin/bash

#define YELLOW	"\033[1;33m"
#define WHITE	"\033[1;37m"
#define RED	"\033[1;31m"
#define GREEN	"\033[1;32m"
#define BLUE	"\034[1;32m"

if [ $# -eq 0 ]; then
    echo -e "\033[1;31m No arguments provided \033[1;37m"
    exit 1
fi

FILE=$1
if [ -f $FILE ]
then
  clear
  echo -e "\033[5;36m ██████╗ ███╗   ███╗██╗ ██████╗██╗  ██╗███████╗ █████╗ ██╗"
  echo -e "\033[5;36m ██╔══██╗████╗ ████║██║██╔════╝██║  ██║██╔════╝██╔══██╗██║"
  echo -e "\033[5;36m ██████╔╝██╔████╔██║██║██║     ███████║█████╗  ███████║██║"
  echo -e "\033[5;36m ██╔══██╗██║╚██╔╝██║██║██║     ██╔══██║██╔══╝  ██╔══██║██║"
  echo -e "\033[5;36m ██████╔╝██║ ╚═╝ ██║██║╚██████╗██║  ██║███████╗██║  ██║███████╗"
  echo -e "\033[5;36m ╚═════╝ ╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ \n \033[1;37m"

  if grep -q "ft::$2" $FILE
  then
    clang++ -Wall -Wextra -Werror -std=c++98 $FILE && ./a.out > my_out
    echo -e " clang++ -Wall -Wextra -Werror -std=c++98 $FILE\n"
    sed -i '' 's/[a-zA-Z]*::'$2'/std::'$2'/g' $FILE
    echo -e "\033[1;37m change to \033[1;33m std:: \033[1;37m namespace \033[1;37m\n"
    clang++ $FILE && ./a.out > std_out

    # check differences
    diff my_out std_out
      ret=$?
      if [[ $ret -eq 0 ]]; then
          echo -e "\033[1;32m NO differences! Well Done \033[1;37m\n"
      else
          echo -e "\033[1;31m Test Failed \033[1;37m\n"
      fi

    rm a.out my_out std_out

# ==============================================================================
  elif grep -q "std::$2" $FILE
  then
    sed -i '' 's/[a-zA-Z]*::'$2'/ft::'$2'/g' $FILE
    echo -e "\033[1;37m change back to \033[1;32m ft:: \033[1;37m namespace \033[1;37m\n"
  fi

else
  echo -e "\033[1;31m $FILE doesn't exist \033[1;37m"
fi