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
import com.project.l02gr08.viewer.gameviewer.ChoiceViewer;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;

public class WhiteChoiceTest implements GameControllerTest {
    private WhiteChoiceController c;
    private ChoiceState s;
    private Game g;
    private Piece p;

    @BeforeEach
    void setUp() {
        p = Mockito.mock(Piece.class);
        Board b = Mockito.mock(Board.class);
        g = Mockito.mock(Game.class);
        c = new WhiteChoiceController();
        s = new ChoiceState(c, Mockito.mock(ChoiceViewer.class), b);

        Mockito.when(g.getState()).thenReturn((State) s);
        Mockito.when(b.pieceAt(Mockito.any(Position.class))).thenReturn(Optional.ofNullable(p));
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
        testWrongInput(s, c, g);
    }

    @Override
    @Test
    public void testENTER() throws NoSuchElementException {
        // Test invalid positions
        Mockito.when(p.getTeam()).thenReturn(Piece.Team.WHITE);
        Mockito.when(p.generateRecommendedMoves(Mockito.any(Board.class)))
                .thenReturn(new ArrayList<>());
        c.step(new KeyStroke(KeyType.Enter), g);
        Mockito.verify(g, Mockito.never()).setState(Mockito.any(PositionState.class));

        // Test invalid team
        Mockito.when(p.getTeam()).thenReturn(Piece.Team.BLACK);
        Mockito.when(p.generateRecommendedMoves(Mockito.any(Board.class)))
                .thenReturn(List.of(new Position(0, 0)));
        c.step(new KeyStroke(KeyType.Enter), g);
        Mockito.verify(g, Mockito.never()).setState(Mockito.any(PositionState.class));

        // Test correct team and valid positions
        Mockito.when(p.getTeam()).thenReturn(Piece.Team.WHITE);
        Mockito.when(p.generateRecommendedMoves(Mockito.any(Board.class)))
                .thenReturn(List.of(new Position(0, 0)));
        c.step(new KeyStroke(KeyType.Enter), g);
        Mockito.verify(g, Mockito.atLeastOnce()).setState(Mockito.any(PositionState.class));
    }

    @Override
    @Test
    public void testWrongKey() throws NoSuchElementException {
        testWrongInput(s, c, g);
    }
}
