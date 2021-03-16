#!/bin/bash

YELLOW="\033[1;33m"
RED="\033[1;31m"
GREEN="\033[1;32m"
BLUE="\034[1;32m"
OTHER="\033[5;36m"
WHITE="\033[0m"

if [ $# -eq 0 ]; then
    echo -e "$RED No arguments provided $WHITE"
    exit 1
fi

FILE=$1
if [ -f $FILE ]
then
  clear
  echo -e "$OTHER ██████╗ ███╗   ███╗██╗ ██████╗██╗  ██╗███████╗ █████╗ ██╗"
  echo -e " ██╔══██╗████╗ ████║██║██╔════╝██║  ██║██╔════╝██╔══██╗██║"
  echo -e " ██████╔╝██╔████╔██║██║██║     ███████║█████╗  ███████║██║"
  echo -e " ██╔══██╗██║╚██╔╝██║██║██║     ██╔══██║██╔══╝  ██╔══██║██║"
  echo -e " ██████╔╝██║ ╚═╝ ██║██║╚██████╗██║  ██║███████╗██║  ██║███████╗"
  echo -e " ╚═════╝ ╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ \n $WHITE"

  if grep -q "ft::$2" $FILE
  then
    clang++ -Wall -Wextra -Werror -std=c++98 $FILE && ./a.out > my_out
    echo -e " clang++ -Wall -Wextra -Werror -std=c++98 $FILE\n"
    sed -i '' 's/[a-zA-Z]*::'$2'/std::'$2'/g' $FILE
    echo -e " change to $GREEN std:: $WHITE namespace \n"
    clang++ $FILE && ./a.out > std_out

    diff my_out std_out
      ret=$?
      if [[ $ret -eq 0 ]]; then
          echo -e "$GREEN NO differences! Well Done $WHITE\n"
      else
          echo -e "$RED Test Failed $WHITE\n"
      fi

    rm a.out my_out std_out

# ==============================================================================
  elif grep -q "std::$2" $FILE
  then
    sed -i '' 's/[a-zA-Z]*::'$2'/ft::'$2'/g' $FILE
    echo -e "$WHITE change back to $GREEN ft:: $WHITE namespace \n"
  fi

else
  echo -e "$RED $FILE doesn't exist $WHITE"
fi