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
  echo -e "\033[1;33m ██████╗ ███╗   ███╗██╗ ██████╗██╗  ██╗███████╗ █████╗ ██╗"
  echo -e "\033[1;33m ██╔══██╗████╗ ████║██║██╔════╝██║  ██║██╔════╝██╔══██╗██║"
  echo -e "\033[1;33m ██████╔╝██╔████╔██║██║██║     ███████║█████╗  ███████║██║"
  echo -e "\033[1;33m ██╔══██╗██║╚██╔╝██║██║██║     ██╔══██║██╔══╝  ██╔══██║██║"
  echo -e "\033[1;33m ██████╔╝██║ ╚═╝ ██║██║╚██████╗██║  ██║███████╗██║  ██║███████╗"
  echo -e "\033[1;33m ╚═════╝ ╚═╝     ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ \n \033[1;37m"

  if grep -q "ft::$2" $FILE
  then
    clang++ $FILE && ./a.out > my_out
    sed -i '' 's/[a-zA-Z]*::'$2'/std::'$2'/g' $FILE
    echo -e "\033[1;37m Change to std:: namespace \033[1;37m"
    clang++ $FILE && ./a.out > std_out

    # check differences
    diff my_out std_out
      ret=$?
      if [[ $ret -eq 0 ]]; then
          echo -e "\033[1;32m NO differences! Well Done \033[1;37m"
      else
          echo -e "\033[1;31m Test Failed \033[1;37m"
      fi

    rm a.out my_out std_out

# ==============================================================================
  elif grep -q "std::$2" $FILE
  then
    sed -i '' 's/[a-zA-Z]*::'$2'/ft::'$2'/g' $FILE
    echo -e "\033[1;37m Change back to ft:: namespace \033[1;37m"
  fi

else
  echo -e "\033[1;31m $FILE doesn't exist \033[1;37m"
fi