package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.MenuState;
import com.project.l02gr08.viewer.MenuViewer;

public class HelpController implements Controller {
    @Override
    public void step(KeyStroke key, Game game) {
        KeyType input = key.getKeyType();
        if (input == KeyType.Escape) {
            MenuState nextState = new MenuState(new MenuController(), new MenuViewer());
            game.setState(nextState);
        }
    }
}
