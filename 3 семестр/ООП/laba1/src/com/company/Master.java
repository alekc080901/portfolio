package com.company;

public class Master {
    private final String NAME;
    private Pet[] petsArray = {};

    public Master(String name) {
        this.NAME = name;
    }

    public void addPet(Pet p) {
        Pet[] petsNewArray = new Pet[petsArray.length + 1];
        System.arraycopy(petsArray, 0, petsNewArray, 0, petsArray.length);
        petsNewArray[petsArray.length] = p;
        this.petsArray = petsNewArray;
    }


    public void takeCare(Pet p) {
        if (p.getMood() == Moods.Dead) {
            System.out.println("This pet is dead.");
            return;
        }

        int newHealth = p.getHealth() + 1;
        p.setHealth(newHealth);
    }

    public void forgetCare(Pet p) {
        if (p.getMood() == Moods.Dead)
            return;

        int newHealth = p.getHealth() - 1;

        p.setHealth(newHealth);
    }

    public void bury(Pet p) {
        if (petsArray.length == 0) {
            System.out.println("There is no one to bury.");
            return;
        }

        int index = -1;
        for (int i = 0; i < petsArray.length; i++)
            if (p == petsArray[i] && p.getMood() == Moods.Dead)
                index = i;
        if (index == -1) {
            System.out.println("This pet is alive.");
            return;
        }

        Pet[] petsNewArray = new Pet[petsArray.length - 1];
        System.arraycopy(petsArray, 0, petsNewArray, 0, index);
        System.arraycopy(petsArray, index + 1, petsNewArray, index, petsArray.length - index - 1);

        this.petsArray = petsNewArray;
        System.out.println("Rest in peace, " + p.getName() + "...");
    }

    public Pet[] getPets() {
        return this.petsArray;
    }
}
