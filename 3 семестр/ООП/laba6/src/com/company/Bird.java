package com.company;

public abstract class Bird implements WishingZoo {
    private final String NAME;

    public Bird(String NAME){
        this.NAME = NAME;
    }

    public abstract void motion();

    @Override
    public String getNAME() {
        return NAME;
    }

    @Override
    public String toString() {
        return String.format("%s (%s)", NAME, this.getClass());
    }
}
