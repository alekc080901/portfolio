package com.company;

import java.util.Scanner;

public class Main {

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

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        // СОЗДАНИЕ ОБЪЕКТОВ КЛАССОВ И ИХ СВЯЗЫВАНИЕ
	    Director dir = new Director("Мирослав", "Прокопьев", 50, Sex.Male);
        Firm firm = new Firm("Сбербанк", dir);
        Employee emp1 = new Employee("Пульхерия", "Подшивалова", 32, Sex.Female);
        Employee emp2 = new Employee("Архип", "Савенков", 40, Sex.Male);
        Employee emp3 = new Employee("Александр", "Соловьев", 26, Sex.Male);
        Employee emp4 = new Employee("Клара", "Витюгова", 62, Sex.Female);

        dir.hireEmployee(firm, emp1);
        dir.hireEmployee(firm, emp2);
        dir.hireEmployee(firm, emp3);
        dir.hireEmployee(firm, emp4);

        System.out.println("Список работников:");
        firm.getEmployees().forEach(System.out::println);
        System.out.println("\nДиректор: " + firm.getDirector());

        System.out.println("\nЧтобы продолжить, нажмите Enter");
        input.nextLine();

        // УВОЛЬНЕНИЕ И ВЫХОД НА ПЕНСИЮ
        emp1.resign(firm);
        emp2.retire(firm);
        emp4.retire(firm);
        dir.fireEmployee(firm, emp3);

        System.out.println("\nСписок работников:");
        firm.getEmployees().forEach(System.out::println);

        System.out.println("\nЧтобы продолжить, нажмите Enter");
        input.nextLine();
    }
}
