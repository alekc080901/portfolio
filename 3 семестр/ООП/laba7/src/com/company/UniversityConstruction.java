package com.company;

public abstract class UniversityConstruction {
    private final int NUMBER;
    private final String NAME;

    public UniversityConstruction(int number, String name) {
        this.NUMBER = number;
        this.NAME = name;
    }

    public int getNUMBER() {
        return NUMBER;
    }

    public String getNAME() {
        return NAME;
    }

    @Override
    public String toString() {
        return String.format("Номер: %d, название: %s (%s)\n", NUMBER, NAME, this.getClass());
    }
}
