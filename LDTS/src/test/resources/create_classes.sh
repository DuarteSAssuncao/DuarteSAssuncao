#!/bin/bash

# Copyright (c) 2023 Guilherme Matos
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE. 

PREFIX="../java/com/project/l02gr08"

if [ $1 == "clean" ]; then
  rm -rf $PREFIX/*
  echo "Deleting All"
  exit
fi


state=(
  "State"
  "GameState"
)

view=(
  "Viewer"
)

view_gameviewer=(
  "GameViewer"
  "WhiteChoiceViewer"
  "WhitePositionViewer"
  "BlackPositionViewer"
  "BlackChoiceViewer"
)

controller=(
  "Controller"
  "WhiteChoiceController"
  "WhitePositionController"
  "BlackPositionController"
  "BlackChoiceController"
)

model=(
  "Board"
  "Position"
)

model_pieces=(
  "Piece"
  "King"
  "Queen"
  "Rook"
  "Bishop"
  "Knight"
  "Pawn"
)

mkdir -p ${PREFIX}/controller
for file in "${controller[@]}"; do
  if [ ! -e "${PREFIX}/controller/${file}Test.java" ]; then
    echo "Creating: ${PREFIX}/controller/${file}Test.java"
    echo "
package com.project.l02gr08.controller; 
import org.junit.jupiter.api.Assertions; 
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class ${file}Test {}
" >> ${PREFIX}/controller/${file}Test.java
  fi
done

mkdir -p ${PREFIX}/state
for file in "${state[@]}"; do
  if [ ! -e "${PREFIX}/state/${file}Test.java" ]; then
    echo "Creating: ${PREFIX}/state/${file}Test.java"
    echo  "
package com.project.l02gr08.state;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class ${file}Test {}
" >> ${PREFIX}/state/${file}Test.java
  fi
done

mkdir -p ${PREFIX}/view
for file in "${view[@]}"; do
  if [ ! -e "${PREFIX}/view/${file}Test.java" ]; then
    echo "Creating: ${PREFIX}/view/${file}Test.java"
    echo "
package com.project.l02gr08.view;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class ${file}Test {}
" >> ${PREFIX}/view/${file}Test.java
  fi
done

mkdir -p ${PREFIX}/view/gameviewer
for file in "${view_gameviewer[@]}"; do
  if [ ! -e "${PREFIX}/view/gameviewer/${file}Test.java" ]; then
    echo "Creating: ${PREFIX}/view/gameviewer/${file}Test.java"
    echo "
package com.project.l02gr08.view.gameviewer;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class ${file}Test {}
" >> ${PREFIX}/view/gameviewer/${file}Test.java
  fi
done


mkdir -p ${PREFIX}/model
for file in "${model[@]}"; do
  if [ ! -e "${PREFIX}/model/${file}Test.java" ]; then
    echo "Creating: ${PREFIX}/model/${file}Test.java"
    echo "
package com.project.l02gr08.model;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class ${file}Test {}
" >> ${PREFIX}/model/${file}Test.java
  fi
done

mkdir -p ${PREFIX}/model/pieces
for file in "${model_pieces[@]}"; do
  if [ ! -e "${PREFIX}/model/pieces/${file}Test.java" ]; then
    echo "Creating: ${PREFIX}/model/pieces/${file}Test.java"
    echo "
package com.project.l02gr08.model.pieces;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
public class ${file}Test {}
" >> ${PREFIX}/model/pieces/${file}Test.java
  fi
done


echo "Done"
