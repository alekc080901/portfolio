package com.company;

public class Controller {

    private static final InformationExpert expert = new InformationExpert();

    public static void addQuestion(Question question) {
        expert.addQuestion(question);
    }

    public static String getForm() {
        return expert.getForm();
    }

}
