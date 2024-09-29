package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.MenuState;

public class MenuController implements Controller {
    @Override
    public void step(KeyStroke key, Game game) {
        MenuState state = (MenuState) game.getState();
        KeyType key_info = key.getKeyType();
        switch (key_info) {
            case ArrowUp:
                state.setSelection(state.getSelection() - 1);
                return;
            case ArrowDown:
                state.setSelection(state.getSelection() + 1);
                return;
            case Enter:
                state.selAction(game);
                return;
            default:
        }
    }

}
