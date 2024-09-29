package com.project.l02gr08.controller.gamecontroller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.state.gamestate.ChoiceState;
import com.project.l02gr08.state.gamestate.PositionState;
import com.project.l02gr08.state.State;
import com.project.l02gr08.viewer.gameviewer.PositionViewer;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import java.util.NoSuchElementException;
import java.util.List;
import java.util.Optional;

public class WhitePositionTest implements GameControllerTest {
    private WhitePositionController c;
    private PositionState s;
    private Game g;
    private Board b;
    private Piece p;

    @BeforeEach
    void setUp() {
        g = Mockito.mock(Game.class);
        b = Mockito.mock(Board.class);
        p = Mockito.mock(Piece.class);
        c = new WhitePositionController();
        s = new PositionState(c, Mockito.mock(PositionViewer.class), b, p);

        Mockito.when(g.getState()).thenReturn((State) s);
        Mockito.when(b.pieceAt(Mockito.any(Position.class))).thenReturn(Optional.ofNullable(p));
        s.setCursor(new Position(0, 0));
    }

    @Override
    @Test
    public void testMovement() throws NoSuchElementException {
        testUpMovement(s, c, g);
        testDownMovement(s, c, g);
        testLeftMovement(s, c, g);
        testRightMovement(s, c, g);
    }

    @Override
    @Test
    public void testESC() throws NoSuchElementException {
        c.step(new KeyStroke(KeyType.Escape), g);
        Mockito.verify(g, Mockito.atLeastOnce()).setState(Mockito.any(ChoiceState.class));
    }

    @Override
    @Test
    public void testENTER() throws NoSuchElementException {
        // Test invalid positions
        Mockito.when(p.generateRecommendedMoves(b)).thenReturn(List.of(new Position(1, 1)));
        c.step(new KeyStroke(KeyType.Enter), g);
        Mockito.verify(g, Mockito.never()).setState(Mockito.any(ChoiceState.class));

        // Test valid positions
        Mockito.when(p.generateRecommendedMoves(b)).thenReturn(List.of(new Position(0, 0)));
        c.step(new KeyStroke(KeyType.Enter), g);
        Mockito.verify(g, Mockito.atLeastOnce()).setState(Mockito.any(ChoiceState.class));
    }

    @Override
    @Test
    public void testWrongKey() throws NoSuchElementException {
        testWrongInput(s, c, g);
    }
}
