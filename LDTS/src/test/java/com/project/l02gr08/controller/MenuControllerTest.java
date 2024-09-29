package com.project.l02gr08.controller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.project.l02gr08.state.MenuState;
import com.project.l02gr08.viewer.MenuViewer;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

public class MenuControllerTest {
    private MenuController c;
    private MenuState s;
    private Game g;

    @BeforeEach
    void setUp() {
        c = new MenuController();
        s = new MenuState(c, Mockito.mock(MenuViewer.class));
        s.setSelection(0);
        g = new Game(s, Mockito.mock(GUI.class));
    }

    @Test
    void testWrongInput() {
        c.step(new KeyStroke(KeyType.Escape), g);
        Assertions.assertEquals(0, s.getSelection());
        Assertions.assertEquals(s, g.getState());
    }

    @Test
    void testENTER() {
        c.step(new KeyStroke(KeyType.Enter), g);
        Assertions.assertNotEquals(s, g.getState());
    }

    @Test
    void testUP() {
        c.step(new KeyStroke(KeyType.ArrowUp), g);
        Assertions.assertEquals(2, s.getSelection());
        c.step(new KeyStroke(KeyType.ArrowUp), g);
        Assertions.assertEquals(1, s.getSelection());
        c.step(new KeyStroke(KeyType.ArrowUp), g);
        Assertions.assertEquals(0, s.getSelection());
    }

    @Test
    void testDOWN() {
        c.step(new KeyStroke(KeyType.ArrowDown), g);
        Assertions.assertEquals(1, s.getSelection());
        c.step(new KeyStroke(KeyType.ArrowDown), g);
        Assertions.assertEquals(2, s.getSelection());
        c.step(new KeyStroke(KeyType.ArrowDown), g);
        Assertions.assertEquals(0, s.getSelection());
    }
}
