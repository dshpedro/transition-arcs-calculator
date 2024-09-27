#!/bin/bash

reference_program="./arcs.out"
student_program=""

args_list=(
  "a*b + !a*c"
  "x*w + x*y"
  "a*!b + !a*b"
  "!a+!b"
  "a*b + c*d + e*f"
  "x*y + z*!w + u*v"
  "p*q + r*s + t*!u*w"
  "a*b + c*d + e*f + g*h + i*j"
  "!a*b + c*d + e*f + g*h"
  "x*!y + z*u + v*w + t*!u"
  "p*q*r + s*t*u + v*w*x"
  "!x*y + z*!w + u*v + p*q"
  "a*b*c + d*e*f + g*h*i"
  "!p*q + r*s + t + u*v*w"
)

all_same=true

for args in "${args_list[@]}"; do
  output_reference=$($reference_program "$args")
  output_student=$($student_program "$args")

  if [ "$output_reference" != "$output_student" ]; then
    echo "Mismatch for expression: '$args'"
    echo -e "Reference output:\n$output_reference"
    echo -e "Student output:\n$output_student"
    all_same=false
  else
    echo "Output match for expression: '$args'"
  fi
done

if [ "$all_same" = true ]; then
  echo "All outputs are the same!"
else
  echo "Some outputs differ!"
fi

