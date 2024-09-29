package com.project.l02gr08.viewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.project.l02gr08.controller.HelpController;
import com.project.l02gr08.state.HelpState;
import com.project.l02gr08.state.State;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.io.IOException;

public class HelpViewerTest {
    private Game game;
    private HelpViewer helpViewer;
    private Screen screen;
    private TextGraphics graphics;

    @BeforeEach
    void setup() {
        game = Mockito.mock(Game.class);
        GUI gui = Mockito.mock(GUI.class);
        screen = Mockito.mock(Screen.class);
        graphics = Mockito.mock(TextGraphics.class);

        State helpState = new HelpState(new HelpController(), new HelpViewer());
        helpViewer = new HelpViewer();

        Mockito.when(game.getGUI()).thenReturn(gui);
        Mockito.when(game.getState()).thenReturn(helpState);
        Mockito.when(gui.getScreen()).thenReturn(screen);
        Mockito.when(screen.newTextGraphics()).thenReturn(graphics);
        Mockito.when(graphics.getSize()).thenReturn(new TerminalSize(88, 88));
    }

    @Test
    void testDraw() throws IOException {
        helpViewer.draw(game);

        Mockito.verify(graphics, Mockito.times(1)).putString(Mockito.eq(new TerminalPosition(2, 2)), Mockito.eq(" HELP "));
        Mockito.verify(graphics, Mockito.times(1)).putString(Mockito.eq(new TerminalPosition(2, 20)), Mockito.eq(" CONTROLS "));
        Mockito.verify(graphics, Mockito.times(1)).putString(Mockito.eq(new TerminalPosition(2, 34)), Mockito.eq(" MORE INFO "));
        Mockito.verify(graphics, Mockito.atLeastOnce()).putString(Mockito.any(TerminalPosition.class), Mockito.anyString());
        Mockito.verify(graphics, Mockito.times(3)).setForegroundColor(new TextColor.RGB(0, 0, 0));
        Mockito.verify(graphics, Mockito.times(3)).setBackgroundColor(new TextColor.RGB(155, 155, 155));
        Mockito.verify(graphics, Mockito.times(3)).setForegroundColor(new TextColor.RGB(155, 155, 155));
        Mockito.verify(graphics, Mockito.times(3)).setBackgroundColor(new TextColor.RGB(0, 0, 0));
        Mockito.verify(screen, Mockito.times(1)).clear();
        Mockito.verify(screen, Mockito.times(1)).refresh(Mockito.any(Screen.RefreshType.class));
    }
}
