
package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.model.pieces.Piece.Team;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertInstanceOf;

import java.util.ArrayList;
import java.util.List;

public class PawnTest implements PieceTest {
    Board emptyBoard;
    List<Position> emptyExpectedWhite;
    List<Position> emptyExpectedBlack;
    Board filledSameBoard;
    List<Position> filledSameExpected;
    Board filledDifferentBoard;
    List<Position> filledDifferentExpected;
    Board initialBoard;
    List<Position> initialWhiteExpected;
    List<Position> initialBlackExpected;
    Board upgradeBoard;

    @Override
    @BeforeEach
    public void setUp() {
        List<Piece> pieces = List.of(
                new Pawn(Piece.Team.WHITE, new Position(3, 3)),
                new Pawn(Piece.Team.BLACK, new Position(3, 4))
        );
        emptyBoard = new Board(pieces);
        emptyExpectedWhite = List.of(new Position(3, 2), new Position(3, 1));
        emptyExpectedBlack = List.of(new Position(3, 5), new Position(3, 6));

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                pieces.add(new Pawn(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledSameBoard = new Board(pieces);
        filledSameExpected = new ArrayList<>();

        pieces = new ArrayList<>();
        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j < 7; ++j) {
                if (i == 3 && j == 3) {
                    pieces.add(new Pawn(Piece.Team.BLACK, new Position(i, j)));
                }
                pieces.add(new Pawn(Piece.Team.WHITE, new Position(i, j)));
            }
        }
        filledDifferentBoard = new Board(pieces);
        filledDifferentExpected = List.of(new Position(2, 4), new Position(4, 4));

        initialBoard = new Board();
        initialWhiteExpected = List.of(
                new Position(0, 5),
                new Position(0, 4)
        );
        initialBlackExpected = List.of(
                new Position(0, 2),
                new Position(0, 3)
        );
        List<Piece> tmp = new ArrayList<>();
        tmp.add(new Pawn(Team.WHITE, new Position(0,1)));
        tmp.add(new Pawn(Team.BLACK, new Position(0,6)));
        upgradeBoard = new Board(tmp);
    }

    @Override
    @Test
    public void testInEmptyBoard() {
        Piece white = emptyBoard.pieceAt(new Position(3, 3)).get();
        Piece black = emptyBoard.pieceAt(new Position(3, 4)).get();
        List<Position> legalMoves = white.generateMoves(emptyBoard);
        Assertions.assertTrue(isSame(legalMoves, emptyExpectedWhite));
        legalMoves = black.generateMoves(emptyBoard);
        Assertions.assertTrue(isSame(legalMoves, emptyExpectedBlack));
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
        Piece white = initialBoard.pieceAt(new Position(0, 6)).get();
        Piece black = initialBoard.pieceAt(new Position(0, 1)).get();
        List<Position> legalWhiteMoves = white.generateMoves(initialBoard);
        List<Position> legaBlackMoves = black.generateMoves(initialBoard);
        Assertions.assertTrue(isSame(legalWhiteMoves, initialWhiteExpected));
        Assertions.assertTrue(isSame(legaBlackMoves, initialBlackExpected));

    }
    
    @Override
    @Test
    public void hasDrawing() {
        Piece piece = emptyBoard.pieceAt(new Position(3, 3)).get();
        Assertions.assertNotNull(piece.getDrawing());
    }

    @Test
    public void upgradeTest() {
        Piece white = upgradeBoard.pieceAt(new Position(0,1)).get();
        Piece black = upgradeBoard.pieceAt(new Position(0,6)).get();
        white.move(upgradeBoard, new Position(0,0));
        black.move(upgradeBoard, new Position(0,7));
        white = upgradeBoard.pieceAt(new Position(0,0)).get();
        black = upgradeBoard.pieceAt(new Position(0,7)).get();
        assertInstanceOf(Queen.class, white);
        assertEquals(Team.WHITE, white.getTeam());
        assertInstanceOf(Queen.class, black);
        assertEquals(Team.BLACK, black.getTeam());

    }

}

