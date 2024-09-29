package com.project.l02gr08.viewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.project.l02gr08.controller.MenuController;
import com.project.l02gr08.state.MenuState;
import com.project.l02gr08.state.State;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.io.IOException;

public class MenuViewerTest {
    private Game game;
    private MenuViewer menuViewer;
    private Screen screen;
    private TextGraphics graphics;

    @BeforeEach
    void setup() {
        game = Mockito.mock(Game.class);
        GUI gui = Mockito.mock(GUI.class);
        screen = Mockito.mock(Screen.class);
        graphics = Mockito.mock(TextGraphics.class);

        State menuState = new MenuState(new MenuController(), new MenuViewer());
        menuViewer = new MenuViewer();

        Mockito.when(game.getGUI()).thenReturn(gui);
        Mockito.when(game.getState()).thenReturn(menuState);
        Mockito.when(gui.getScreen()).thenReturn(screen);
        Mockito.when(screen.newTextGraphics()).thenReturn(graphics);
        Mockito.when(screen.getTerminalSize()).thenReturn(new TerminalSize(88, 88));
    }

    @Test
    void testDraw() throws IOException {
        menuViewer.draw(game);

        Mockito.verify(graphics, Mockito.times(1)).putString(Mockito.eq(new TerminalPosition(39, 29)), Mockito.eq("Start Game"));
        Mockito.verify(graphics, Mockito.times(1)).putString(Mockito.eq(new TerminalPosition(39, 31)), Mockito.eq("Help/Rules"));
        Mockito.verify(graphics, Mockito.times(1)).putString(Mockito.eq(new TerminalPosition(42, 33)), Mockito.eq("Quit"));
        Mockito.verify(graphics, Mockito.times(3)).setBackgroundColor(new TextColor.RGB(0, 0, 0));
        Mockito.verify(graphics, Mockito.times(3)).setForegroundColor(new TextColor.RGB(155, 155, 155));
        Mockito.verify(graphics, Mockito.times(1)).setForegroundColor(new TextColor.RGB(222, 90, 90));
        Mockito.verify(screen, Mockito.times(1)).clear();
        Mockito.verify(screen, Mockito.times(1)).refresh(Mockito.any(Screen.RefreshType.class));
    }
}
