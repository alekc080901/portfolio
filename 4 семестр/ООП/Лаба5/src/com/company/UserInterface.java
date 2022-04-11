package com.company;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class UserInterface {
    private static final Scanner scanner = new Scanner(System.in);

    private static String askHeader() {
        System.out.println("Задайте заголовок вопроса:");
        return scanner.nextLine();
    }

    private static QuestionTypes askType() {
        QuestionTypes type = null;
        boolean isIncorrect = true;

        while (isIncorrect) {
            System.out.println("Укажите тип вопроса ('?' для помощи):");
            String userAnswer = scanner.nextLine();

            switch (userAnswer) {
                case ("?") -> System.out.println("Введите 1 для вопроса с одним вариантом ответа\n" +
                        "Введите 2 для вопроса с несколькими вариантами ответа\n" +
                        "Введите 3 для вопроса с ручным вводом пользователя");

                case ("1") -> {
                    type = QuestionTypes.ONE_CHOICE;
                    isIncorrect = false;
                }

                case ("2") -> {
                    type = QuestionTypes.SEVERAL_CHOICES;
                    isIncorrect = false;
                }

                case ("3") -> {
                    type = QuestionTypes.TEXT_INPUT;
                    isIncorrect = false;
                }

                default -> System.out.println("Введите корректный тип!");
            }
        }
        return type;
    }

    private static Answer askAnswer(QuestionTypes questionType) throws Exception {
        System.out.println("Задайте содержание вопроса.");

        AbstractFactory answerFactory = new AnswerFactory();
        Answer answer;
        switch (questionType) {
            case ONE_CHOICE, SEVERAL_CHOICES -> {
                List<String> answers = new ArrayList<>();
                String answerInput;
                int counter = 1;

                do {
                    System.out.printf("Введите содержание %d первого подпункта (- для выхода):\n", counter);
                    answerInput = scanner.nextLine();

                    if (answerInput.equals("-"))
                        break;

                    answers.add(answerInput);
                    counter++;
                } while (true);

                answer = answerFactory.createOptionAnswer(answers);
            }

            case TEXT_INPUT -> {
                System.out.println("Введите текст вопроса");
                String answerInput = scanner.nextLine();

                answer = answerFactory.createTextAnswer(answerInput);
            }

            default -> throw new Exception("Неверный тип вопроса!");
        }
        return answer;
    }

    private static boolean askRequired() {
        while (true) {
            System.out.println("Обязателен ли вопрос (да/нет)?");
            String requiredInput = scanner.nextLine();

            switch (requiredInput) {
                case "да" -> {
                    return true;
                }

                case "нет" -> {
                    return false;
                }

                default -> System.out.println("Введите да или нет!");
            }
        }
    }

    public void askQuestion() throws Exception {
        while (true) {
            String questionHeader = askHeader();
            QuestionTypes questionType = askType();
            Answer answer = askAnswer(questionType);
            boolean isRequired = askRequired();

            Question question = new Question(questionHeader, questionType, answer, isRequired);
            Controller.addQuestion(question);
            showForm();
        }
    }

    private void showForm() {
        System.out.println(Controller.getForm());
    }
}
