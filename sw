#!/bin/sh

# Credit for https://github.com/salman-abedin/devour

id=$(xdo id)
xdo hide
$("$@") > /dev/null 2>&1
xdo show "$id"

