
package com.project.l02gr08.viewer.gameviewer;

import com.googlecode.lanterna.TerminalPosition;
import com.googlecode.lanterna.TerminalSize;
import com.googlecode.lanterna.TextColor;
import com.googlecode.lanterna.graphics.TextGraphics;
import com.googlecode.lanterna.screen.Screen;
import com.project.l02gr08.controller.gamecontroller.WhiteChoiceController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.*;
import com.project.l02gr08.state.gamestate.ChoiceState;
import com.project.l02gr08.state.State;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.util.ArrayList;
import java.util.List;

public class GameViewerTest {
    private State gameState;
    private GameViewer gameViewer;
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

    private Board getCheckBoard() {
        List<Piece> pieces = new ArrayList<>();
        pieces.add(new Rook(Piece.Team.WHITE, new Position(0, 0)));
        pieces.add(new Rook(Piece.Team.WHITE, new Position(1, 0)));
        pieces.add(new King(Piece.Team.WHITE, new Position(2, 0)));
        pieces.add(new King(Piece.Team.BLACK, new Position(1, 3)));
        return new Board(pieces);
    }

    @BeforeEach
    void setup() {
        screen = Mockito.mock(Screen.class);
        graphics = Mockito.mock(TextGraphics.class);

        gameState = Mockito.spy(new ChoiceState(new WhiteChoiceController(), new ChoiceViewer(), getInitialBoard()));
        gameViewer = Mockito.spy(new ChoiceViewer());

        Mockito.when(screen.newTextGraphics()).thenReturn(graphics);
        Mockito.when(screen.getTerminalSize()).thenReturn(new TerminalSize(88, 88));
    }

    @Test
    void testDrawBoard() {
        gameViewer.drawBoard(screen, (ChoiceState) gameState);

        Mockito.verify(graphics, Mockito.times(32)).setBackgroundColor(new TextColor.RGB(191, 153, 114));
        Mockito.verify(graphics, Mockito.times(32)).setBackgroundColor(new TextColor.RGB(93, 47, 39));
        Mockito.verify(graphics, Mockito.times(64)).fillRectangle(Mockito.any(TerminalPosition.class), Mockito.eq(new TerminalSize(11, 11)), Mockito.eq(' '));
    }

    @Test
    void testDrawPiece() {
        gameViewer.drawPiece(screen, ((ChoiceState) gameState).getBoard().pieceAt(new Position(0, 0)).get());

        Mockito.verify(graphics, Mockito.atLeastOnce()).setCharacter(Mockito.any(TerminalPosition.class), Mockito.anyChar());
        Mockito.verify(graphics, Mockito.times(1)).setForegroundColor(new TextColor.RGB(204, 0, 0));
        Mockito.verify(graphics, Mockito.times(1)).setBackgroundColor(new TextColor.RGB(0, 0, 0));
    }

    @Test
    void testDrawCursor() {
        gameViewer.drawCursor(screen, (ChoiceState) gameState);

        Mockito.verify(graphics, Mockito.times(1)).setBackgroundColor(new TextColor.RGB(152, 251, 152));
        Mockito.verify(graphics, Mockito.times(1)).drawRectangle(Mockito.eq(new TerminalPosition(0, 77)), Mockito.eq(new TerminalSize(11, 11)), Mockito.anyChar());
    }

    @Test
    void testDrawCheck() {
        gameViewer.drawCheck(screen, (King) ((ChoiceState) gameState).getBoard().pieceAt(new Position(4, 0)).get(), ((ChoiceState) gameState).getBoard());

        Mockito.verify(graphics, Mockito.never()).setBackgroundColor(Mockito.any(TextColor.class));
        Mockito.verify(graphics, Mockito.never()).fillRectangle(Mockito.any(TerminalPosition.class), Mockito.any(TerminalSize.class), Mockito.anyChar());

        ChoiceState boardInCheckState = new ChoiceState(new WhiteChoiceController(), new ChoiceViewer(), getCheckBoard());
        gameViewer.drawCheck(screen, (King) boardInCheckState.getBoard().pieceAt(new Position(1, 3)).get(), boardInCheckState.getBoard());

        Mockito.verify(graphics, Mockito.times(1)).setBackgroundColor(new TextColor.RGB(128, 0, 1));
        Mockito.verify(graphics, Mockito.times(1)).fillRectangle(Mockito.eq(new TerminalPosition(11, 33)), Mockito.eq(new TerminalSize(11, 11)), Mockito.anyChar());
        Mockito.verify(gameViewer, Mockito.times(1)).drawPiece(Mockito.any(Screen.class), Mockito.any(Piece.class));
    }
}

