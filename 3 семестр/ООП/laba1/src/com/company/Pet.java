package com.company;

import java.util.Random;

public class Pet {
    private final static int MAX_HEALTH = 10;
    private final static int MIN_HEALTH = 0;
    private final String NAME;

    private int health;
    private Moods mood;

    public Pet(String name) {
        Random random = new Random();
        this.health = random.nextInt(9) + 1;
        this.NAME = name;
        checkMood();
    }

    public void checkMood() {
        if (this.health <= 3 && this.health >= 0)
            this.mood = Moods.Bad;

        else if (this.health <= 7 && this.health >= 4)
            this.mood = Moods.Good;

        else if (this.health <= MAX_HEALTH && this.health >= 8)
            this.mood = Moods.Perfect;

        else if (this.health < MIN_HEALTH)
            this.mood = Moods.Dead;
    }

    public int getHealth() {
        return this.health;
    }

    public void setHealth(int health) {
        if (health > MAX_HEALTH)
            return;
        this.health = health;
        checkMood();
    }

    public Moods getMood() {
        return this.mood;
    }

    public String getName() {
        return this.NAME;
    }
}
