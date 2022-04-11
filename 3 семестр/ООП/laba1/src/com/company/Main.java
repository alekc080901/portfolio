package com.company;

import java.util.Scanner;

public class Main {
    private static final String MY_NAME = "Alexander";

    public static int inputNat() {
        Scanner in = new Scanner(System.in);

        int x;
        while (true) {
            try {
                x = in.nextInt();
                in.nextLine();

                if (x < 0)
                    throw new java.util.InputMismatchException("Value is below zero");
                break;

            } catch (java.util.InputMismatchException e) {
                System.out.println("Input the correct value");
                in.nextLine();
            }
        }
        return x;
    }

    public static Pet petChoiceMenu(Pet[] pets) {
        while (true) {
            Scanner in = new Scanner(System.in);

            for (int i = 0; i < pets.length; i++)
                System.out.printf("%d. %s\n", i + 1, pets[i].getName());
            int petChoice = inputNat();

            if (petChoice <= 0) {
                System.out.printf("Input 1-%d", pets.length);
                continue;
            }

            return pets[petChoice - 1];
        }
    }

    public static void main(String[] args) {
        Master me = new Master(MY_NAME);
        Scanner input = new Scanner(System.in);
        while (true) {
            System.out.println("Enter your choice:\n" +
                    "1. Buy a new pet;\n" +
                    "2. Show info about pets;\n" +
                    "3. Take care of your pet;\n" +
                    "4. Forget about your pets;\n" +
                    "5. Bury your pets;\n" +
                    "6. Exit.");
            int choice = inputNat();

            switch (choice) {
                case (1) -> {
                    System.out.println("Name your pet:");
                    String petName = input.nextLine();
                    Pet newPet = new Pet(petName);
                    me.addPet(newPet);
                    System.out.println("Good luck with your new pet!");
                }

                case (2) -> {
                    if (me.getPets().length == 0) {
                        System.out.println("You haven't got any pet.");
                        break;
                    }

                    for (Pet pet : me.getPets()) {
                        System.out.printf("Name: %s; Health: %d; Mood: %s\n",
                                pet.getName(), pet.getHealth(), pet.getMood());
                    }
                }

                case (3) -> {
                    if (me.getPets().length == 0) {
                        System.out.println("You should buy a pet at first.");
                        break;
                    }

                    Pet pet = petChoiceMenu(me.getPets());
                    me.takeCare(pet);
                }

                case (4) -> {
                    if (me.getPets().length == 0) {
                        System.out.println("You should buy a pet at first.");
                        break;
                    }

                    for (Pet pet : me.getPets())
                        me.forgetCare(pet);
                }

                case (5) -> {
                    if (me.getPets().length == 0) {
                        System.out.println("You should buy a pet at first.");
                        break;
                    }

                    Pet pet = petChoiceMenu(me.getPets());
                    me.bury(pet);
                }

                case (6) ->
                    System.exit(0);

                default -> {
                    System.out.println("Введите значение от 1 до 6!");
                    continue;
                }
            }
        }
    }
}
