#!/bin/bash
awk '{print $1}' ~/.bash_history | sort | uniq -c | sort -gr | head -n10

