package com.company;

public class Main {

    public static void main(String[] args) {

        Zoo zoo = new Zoo();

        Cat cat = new Cat("Барсик");
        Lion lion1 = new Lion("Бонифаций");
        Lion lion2 = new Lion("Аркадий");
        Dove dove = new Dove("Иннокентий");
        Penguin penguin = new Penguin("Пен-Пен");

        zoo.addAviary(new ColdAviary(1));
        zoo.addLivingBeings(cat, lion1, lion2, dove, penguin);
        zoo.distribution();
        zoo.display();

        System.out.println("\nЗвуки:");
        cat.say();
        lion1.say();
        dove.motion();
        penguin.motion();
    }
}
