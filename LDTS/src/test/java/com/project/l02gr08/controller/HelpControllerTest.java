package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.MenuState;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

public class HelpControllerTest {
    private HelpController c;
    private Game g;

    @BeforeEach
    void setUp() {
        c = new HelpController();
        g = Mockito.mock(Game.class);
    }

    @Test
    void testESC() {
        c.step(new KeyStroke(KeyType.Escape), g);
        Mockito.verify(g, Mockito.times(1)).setState(Mockito.any(MenuState.class));
    }

    @Test
    void testWrongInput() {
        c.step(KeyStroke.fromString("a"), g);
        Mockito.verify(g, Mockito.times(0)).setState(Mockito.any(MenuState.class));
    }
}
