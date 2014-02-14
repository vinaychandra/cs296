#!/bin/bash
cd ../
rsync -t ./src/* $1/backup/
