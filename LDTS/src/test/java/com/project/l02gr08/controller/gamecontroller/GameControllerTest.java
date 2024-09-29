package com.project.l02gr08.controller.gamecontroller;

import com.googlecode.lanterna.input.KeyStroke;
import com.googlecode.lanterna.input.KeyType;
import com.project.l02gr08.Game;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.state.gamestate.GameState;
import com.project.l02gr08.state.gamestate.PositionState;
import org.junit.jupiter.api.Assertions;
import org.mockito.Mockito;

public interface GameControllerTest {
    void testMovement();
    void testESC();
    void testENTER();
    void testWrongKey();

    // ==================================================================================================

    default void testUpMovement(GameState s, GameController c, Game g) {
        s.setCursor(new Position(0, 0));
        c.step(new KeyStroke(KeyType.ArrowUp), g);
        Assertions.assertEquals(new Position(0, 0), s.getCursor());

        s.setCursor(new Position(0, 7));
        for (int i = 7; i > 0; --i) {
            c.step(new KeyStroke(KeyType.ArrowUp), g);
            Assertions.assertEquals(new Position(0, i - 1), s.getCursor());
        }
    }

    default void testDownMovement(GameState s, GameController c, Game g) {
        s.setCursor(new Position(0, 7));
        c.step(new KeyStroke(KeyType.ArrowDown), g);
        Assertions.assertEquals(new Position(0, 7), s.getCursor());

        s.setCursor(new Position(0, 0));
        for (int i = 0; i < 7; ++i) {
            c.step(new KeyStroke(KeyType.ArrowDown), g);
            Assertions.assertEquals(new Position(0, i + 1), s.getCursor());
        }
    }

    default void testLeftMovement(GameState s, GameController c, Game g) {
        s.setCursor(new Position(0, 0));
        c.step(new KeyStroke(KeyType.ArrowLeft), g);
        Assertions.assertEquals(new Position(0, 0), s.getCursor());

        s.setCursor(new Position(7, 0));
        for (int i = 7; i > 0; --i) {
            c.step(new KeyStroke(KeyType.ArrowLeft), g);
            Assertions.assertEquals(new Position(i - 1, 0), s.getCursor());
        }
    }

    default void testRightMovement(GameState s, GameController c, Game g) {
        s.setCursor(new Position(7, 0));
        c.step(new KeyStroke(KeyType.ArrowRight), g);
        Assertions.assertEquals(new Position(7, 0), s.getCursor());

        s.setCursor(new Position(0, 0));
        for (int i = 0; i < 7; ++i) {
            c.step(new KeyStroke(KeyType.ArrowRight), g);
            Assertions.assertEquals(new Position(i + 1, 0), s.getCursor());
        }
    }

    default void testWrongInput(GameState s, GameController c, Game g) {
        Position cursor = s.getCursor();
        c.step(new KeyStroke(KeyType.Delete), g);

        Mockito.verify(g, Mockito.never()).setState(Mockito.any(PositionState.class));
        Assertions.assertSame(cursor, s.getCursor());
    }



}
