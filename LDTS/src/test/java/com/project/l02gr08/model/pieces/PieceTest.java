
package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Position;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashSet;
import java.util.List;

interface PieceTest {
    @BeforeEach
    void setUp();
    @Test
    void testInEmptyBoard();
    @Test
    void testInFilledSameBoard();
    @Test
    void testInFilledDifferentBoard();
    @Test
    void testInInitialBoard();
    @Test
    void hasDrawing();

    default boolean isSame(List<Position> a, List<Position> b) {
        if (a.size() != b.size()) return false;

        HashSet<Position> hashA = new HashSet<>(a);
        HashSet<Position> hashB = new HashSet<>(b);

        return hashA.equals(hashB);
    }
}

