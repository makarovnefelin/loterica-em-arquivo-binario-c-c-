#!/bin/bash

# Verifica se a mensagem do commit foi passada como argumento
if [ -z "$1" ]; then
  echo "Use: ./gitpush.sh 'mensagem do commit'"
  exit 1
fi

# Adiciona todas as mudanças no stage
git add .

# Faz o commit com a mensagem que você passou
git commit -m "$1"

# Envia as mudanças para o GitHub na branch main
git push origin main