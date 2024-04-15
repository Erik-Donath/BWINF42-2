@echo off
title Die Siedler
color 0F

cls
pip install -r .\requirements

cls
python3 .\src\main.py

pause
exit