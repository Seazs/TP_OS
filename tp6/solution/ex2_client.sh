#!/bin/bash

exec 3<>/dev/tcp/127.0.0.1/8080

read -r line
echo "$line" >&3
read -r reponse <&3
echo "Réponse : $reponse"

exec 3<&-
exec 3>&-
