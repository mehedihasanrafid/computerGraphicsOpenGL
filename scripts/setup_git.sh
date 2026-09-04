#!/usr/bin/env bash
set -euo pipefail

REMOTE_URL="${1:-https://github.com/mehedihasanrafid/computerGraphicsOpenGL.git}"

if [[ -d .git ]]; then
  echo "A Git repository already exists here."
  exit 1
fi

git init
git branch -M main
git add .
git commit -m "Rebuild OpenGL yacht journey as a portfolio project"
git remote add origin "$REMOTE_URL"

echo "Repository initialized. Push with:"
echo "git push -u origin main"
