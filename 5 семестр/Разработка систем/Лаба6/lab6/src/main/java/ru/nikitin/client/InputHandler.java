package ru.nikitin.client;

import ru.nikitin.server.entities.Stationery;

import java.util.Scanner;

public class InputHandler {
    public static String inputString(boolean lower) {
        Scanner in = new Scanner(System.in);
        String text = in.nextLine();
        while (text.equals("")) {
            System.out.println("Поле не должно быть пустым!");
            text = in.nextLine();
        }
        if (lower)
            text = text.toLowerCase();
        return text;
    }

    public static int inputNat(boolean strict) {
        Scanner in = new Scanner(System.in);

        int x;
        while (true) {
            try {
                x = in.nextInt();
                in.nextLine();

                if (x < 0)
                    throw new java.util.InputMismatchException("Value is below zero!");

                if (strict && x <= 0)
                    throw new java.util.InputMismatchException("Value is below zero!");
                break;

            } catch (java.util.InputMismatchException e) {
                System.out.println("Input the correct value!");
                in.nextLine();
            }
        }
        return x;
    }

    public static Double inputDouble(double bottomBound, double upperBound) {
        Scanner in = new Scanner(System.in);

        double x;
        while (true) {
            try {
                x = in.nextDouble();
                in.nextLine();

                if (x < bottomBound || x > upperBound)
                    throw new java.util.InputMismatchException("Incorrect value!");
                break;

            } catch (java.util.InputMismatchException e) {
                System.out.println("Input the correct value!");
                in.nextLine();
            }
        }
        return x;
    }

    public static int inputId() {
        System.out.println("Введите id элемента:");
        return inputNat(false);
    }

    public static Stationery inputStationery() {

        System.out.println("Введите тип канцтовара (обязательное поле):");
        String type = inputString(true);

        System.out.println("Введите подтип канцтовара:");
        String subtype = inputString(true).toLowerCase();

        System.out.println("Введите цену товара (обязательное поле):");
        Double price = inputDouble(0, Double.POSITIVE_INFINITY);

        System.out.println("Введите количество канцтовара на складе:");
        int amount = inputNat(false);

        System.out.println("Введите производителя канцтовара:");
        String manufacturer = inputString(true).toLowerCase();

        return new Stationery(type, subtype, price, amount, manufacturer);
    }
}
