package com.company;

public abstract class Animal implements WishingZoo {
    private final String NAME;

    public Animal(String NAME) {
        this.NAME = NAME;
    }

    public abstract void say();

    @Override
    public String getNAME() {
        return NAME;
    }

    @Override
    public String toString() {
        return String.format("%s (%s)", NAME, this.getClass());
    }
}
