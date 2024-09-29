
package com.project.l02gr08.model;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class PositionTest {
    @Test
    public void combination() {
        Position before = new Position(3, 3);
        Position after = before.getLeft().getRight().getUp().getDown();
        Assertions.assertEquals(before, after);
    }

    @Test
    public void left() {
        Assertions.assertEquals(2, new Position(3, 3).getLeft().getX());
        Assertions.assertEquals(3, new Position(3, 3).getLeft().getY());
    }

    @Test
    public void right() {
        Assertions.assertEquals(4, new Position(3, 3).getRight().getX());
        Assertions.assertEquals(3, new Position(3, 3).getRight().getY());
    }

    @Test
    public void up() {
        Assertions.assertEquals(3, new Position(3, 3).getUp().getX());
        Assertions.assertEquals(2, new Position(3, 3).getUp().getY());
    }

    @Test
    public void down() {
        Assertions.assertEquals(3, new Position(3, 3).getDown().getX());
        Assertions.assertEquals(4, new Position(3, 3).getDown().getY());
    }
}

