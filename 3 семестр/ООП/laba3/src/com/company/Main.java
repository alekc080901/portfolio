package com.company;

import java.util.*;

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

        // Создание деканата
        Deanery deanery = new Deanery();

        // Создание предметов
        Subject math = new Subject("Математика");
        Subject programming = new Subject("Программирование");

        // Создание профессоров
        new Professor("Аркадий Петрович", math, deanery);
        new Professor("Леонид Аркадьевич", programming, deanery);

        // Создание студентов
        new Student("Иван", deanery);
        new Student("Сергей", deanery);
        new Student("Руслан", deanery);
        new Student("Альберт", deanery);
        new Student("Александр", deanery);
        new Student("Владимир", deanery);
        new Student("Михаил", deanery);
        new Student("Никита", deanery);

        while (true) {
            System.out.println("Введите ваш выбор:\n" +
                    "1. Принять экзамен;\n" +
                    "2. Пересдать экзамен;\n" +
                    "3. Вывести список сдавших;\n" +
                    "4. Вывести список несдавших;\n" +
                    "5. Выход.");
            String choice = input.nextLine();

            switch (choice) {
                case ("1"), ("2"), ("3"), ("4") -> {
                    Professor[] professors = deanery.getProfessors();
                    if (professors.length == 0) {
                        System.out.println("Профессоров нет!");
                        break;
                    }

                    int count = 1;
                    System.out.println("Выберите преподавателя:");
                    for (Professor p : deanery.getProfessors()) {
                        System.out.printf("%d. %s\n", count, p.getNAME());
                        count++;
                    }
                    int professorChoice = inputNat();

                    if (professorChoice < 0 || professorChoice > professors.length) {
                        System.out.printf("Корректны значения от 1 до %d!\n\n", professors.length);
                        break;
                    }

                    Professor professor = professors[professorChoice-1];
                    switch (choice) {
                        case "1" -> {
                            professor.startExam(deanery);
                        }

                        case "2" -> {
                            professor.retakeExam(deanery);
                        }

                        case "3" -> {
                            HashMap<Student, Integer> results = professor.getPassedStudents();
                            results.forEach((key, val) -> System.out.println(key.getNAME() + ": " + val));
                        }

                        case "4" -> {
                            Queue<Student> results = professor.getFailedStudents();
                            results.forEach(key -> System.out.println(key.getNAME()));
                        }
                    }
                }
                case ("5") -> System.exit(0);
                default -> System.out.println("Введите значение от 1 до 5!\n");
            }
        }
    }
}
