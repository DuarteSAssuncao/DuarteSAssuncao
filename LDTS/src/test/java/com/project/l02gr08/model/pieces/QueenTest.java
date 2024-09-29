
package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class QueenTest implements PieceTest {
    Board emptyBoard;
    List<Position> emptyExpected;
    Board filledSameBoard;
    List<Position> filledSameExpected;
    Board filledDifferentBoard;
    List<Position> filledDifferentExpected;
    Board initialBoard;
    List<Position> initialExpected;

    @Override
    @BeforeEach
    public void setUp() {
        List<Piece> pieces = List.of(new Queen(Piece.Team.WHITE, new Position(3, 3)));
        emptyBoard = new Board(pieces);
        emptyExpected = List.of(
                new Position(2, 2), new Position(1, 1), new Position(0, 0),
                new Position(3, 2), new Position(3, 1), new Position(3, 0),
                new Position(4, 2), new Position(5, 1), new Position(6, 0),
                new Position(2, 3), new Position(1, 3), new Position(0, 3),
                new Position(4, 3), new Position(5, 3), new Position(6, 3), new Position(7, 3),
                new Position(2, 4), new Position(1, 5), new Position(0, 6),
                new Position(3, 4), new Position(3, 5), new Position(3, 6), new Position(3, 7),
                new Position(4, 4), new Position(5, 5), new Position(6, 6), new Position(7, 7)
        );

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                pieces.add(new Queen(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledSameBoard = new Board(pieces);
        filledSameExpected = new ArrayList<>();

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                if (i == 3 && j == 3) {
                    pieces.add(new Queen(Piece.Team.BLACK, new Position(i, j)));
                }
                pieces.add(new Queen(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledDifferentBoard = new Board(pieces);
        filledDifferentExpected = List.of(
                new Position(2, 2),
                new Position(3, 2),
                new Position(4, 2),
                new Position(2, 3),
                new Position(4, 3),
                new Position(2, 4),
                new Position(3, 4),
                new Position(4, 4)
        );

        initialBoard = new Board();
        initialExpected = new ArrayList<>();
    }

    @Override
    @Test
    public void testInEmptyBoard() {
        Piece piece = emptyBoard.pieceAt(new Position(3, 3)).get();
        List<Position> legalMoves = piece.generateMoves(emptyBoard);
        Assertions.assertTrue(isSame(legalMoves, emptyExpected));
    }

    @Override
    @Test
    public void testInFilledSameBoard() {
        Piece piece = filledSameBoard.pieceAt(new Position(3, 3)).get();
        List<Position> legalMoves = piece.generateMoves(filledSameBoard);
        Assertions.assertTrue(isSame(legalMoves, filledSameExpected));
    }

    @Override
    @Test
    public void testInFilledDifferentBoard() {
        Piece piece = filledDifferentBoard.pieceAt(new Position(3, 3)).get();
        List<Position> legalMoves = piece.generateMoves(filledDifferentBoard);
        Assertions.assertTrue(isSame(legalMoves, filledDifferentExpected));
    }

    @Override
    @Test
    public void testInInitialBoard() {
        Piece piece = initialBoard.pieceAt(new Position(4, 0)).get();
        List<Position> legalMoves = piece.generateMoves(initialBoard);
        Assertions.assertTrue(isSame(legalMoves, initialExpected));
    }

    @Override
    @Test
    public void hasDrawing() {
        Piece piece = emptyBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertNotNull(piece.getDrawing());
    }
}

