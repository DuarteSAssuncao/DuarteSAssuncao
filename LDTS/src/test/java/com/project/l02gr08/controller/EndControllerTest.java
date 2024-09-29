package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.MenuState;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

public class EndControllerTest {
    private EndController c;
    private Game g;

    @BeforeEach
    void setUp() {
        c = new EndController();
        g = Mockito.mock(Game.class);
    }

    @Test
    void testInput() {
        c.step(KeyStroke.fromString("a"), g);
        Mockito.verify(g, Mockito.times(1)).setState(Mockito.any(MenuState.class));
    }
}
