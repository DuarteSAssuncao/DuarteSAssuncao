
package com.project.l02gr08.viewer.gameviewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.GUI;
import com.project.l02gr08.Game;
import com.project.l02gr08.controller.gamecontroller.WhitePositionController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.*;
import com.project.l02gr08.state.gamestate.PositionState;
import com.project.l02gr08.state.State;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class PositionViewerTest {
    private Game game;
    private PositionViewer positionViewer;
    private Screen screen;
    private TextGraphics graphics;

    private Board getInitialBoard() {
        List<Piece> expectedInitial = new ArrayList<>();
        expectedInitial.add(new Rook(Piece.Team.BLACK, new Position(0, 0)));
        expectedInitial.add(new Knight(Piece.Team.BLACK, new Position(1, 0)));
        expectedInitial.add(new Bishop(Piece.Team.BLACK, new Position(2, 0)));
        expectedInitial.add(new Queen(Piece.Team.BLACK, new Position(3, 0)));
        expectedInitial.add(new King(Piece.Team.BLACK, new Position(4, 0)));
        expectedInitial.add(new Bishop(Piece.Team.BLACK, new Position(5, 0)));
        expectedInitial.add(new Knight(Piece.Team.BLACK, new Position(6, 0)));
        expectedInitial.add(new Rook(Piece.Team.BLACK, new Position(7, 0)));
        for (int i = 0; i < 8; ++i) {
            expectedInitial.add(new Pawn(Piece.Team.BLACK, new Position(i, 1)));
        }
        expectedInitial.add(new Rook(Piece.Team.WHITE, new Position(0, 7)));
        expectedInitial.add(new Knight(Piece.Team.WHITE, new Position(1, 7)));
        expectedInitial.add(new Bishop(Piece.Team.WHITE, new Position(2, 7)));
        expectedInitial.add(new Queen(Piece.Team.WHITE, new Position(3, 7)));
        expectedInitial.add(new King(Piece.Team.WHITE, new Position(4, 7)));
        expectedInitial.add(new Bishop(Piece.Team.WHITE, new Position(5, 7)));
        expectedInitial.add(new Knight(Piece.Team.WHITE, new Position(6, 7)));
        expectedInitial.add(new Rook(Piece.Team.WHITE, new Position(7, 7)));
        for (int i = 0; i < 8; ++i) {
            expectedInitial.add(new Pawn(Piece.Team.WHITE, new Position(i, 6)));
        }
        return new Board(expectedInitial);
    }

    @BeforeEach
    void setup() {
        game = Mockito.mock(Game.class);
        GUI gui = Mockito.mock(GUI.class);
        screen = Mockito.mock(Screen.class);
        graphics = Mockito.mock(TextGraphics.class);

        State positionState = Mockito.spy(new PositionState(new WhitePositionController(), new PositionViewer(), getInitialBoard(), getInitialBoard().pieceAt(new Position(1, 7)).get()));
        positionViewer = Mockito.spy(new PositionViewer());

        Mockito.when(game.getGUI()).thenReturn(gui);
        Mockito.when(game.getState()).thenReturn(positionState);
        Mockito.when(positionState.getViewer()).thenReturn(positionViewer);
        Mockito.when(gui.getScreen()).thenReturn(screen);
        Mockito.when(screen.newTextGraphics()).thenReturn(graphics);
        Mockito.when(screen.getTerminalSize()).thenReturn(new TerminalSize(88, 88));
    }

    @Test
    void testDraw() throws IOException {
        positionViewer.draw(game);

        Mockito.verify(positionViewer, Mockito.times(1)).drawCursor(Mockito.any(Screen.class), Mockito.any(PositionState.class));
        Mockito.verify(positionViewer, Mockito.times(32)).drawPiece(Mockito.any(Screen.class), Mockito.any(Piece.class));
        Mockito.verify(graphics, Mockito.times(1)).setBackgroundColor(new TextColor.RGB(130, 130, 130));
        Mockito.verify(graphics, Mockito.times(66)).fillRectangle(Mockito.any(TerminalPosition.class), Mockito.any(TerminalSize.class), Mockito.anyChar());
        Mockito.verify(positionViewer, Mockito.times(2)).drawCheck(Mockito.any(Screen.class), Mockito.any(King.class), Mockito.any(Board.class));
        Mockito.verify(screen, Mockito.times(1)).refresh(Mockito.any(Screen.RefreshType.class));
    }
}

