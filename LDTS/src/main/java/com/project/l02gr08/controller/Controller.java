package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.project.l02gr08.Game;

public interface Controller {
    void step(KeyStroke key, Game game);
}
