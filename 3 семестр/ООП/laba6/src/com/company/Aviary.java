package com.company;

public abstract class Aviary {
    private Exotic being = null;
    private final int NUMBER;

    public Aviary(int NUMBER) {
        this.NUMBER = NUMBER;
    }

    public void occupyAviary(Exotic being) {
        this.being = being;
    }

    public Exotic getBeing() {
        return being;
    }

    public int getNUMBER() {
        return NUMBER;
    }

    @Override
    public String toString() {
        return (being == null) ? String.format("Вольер %d пуст.", NUMBER)
                : String.format("В вольере %d живет %s.", NUMBER, being);
    }
}
