package com.company;

import java.util.List;

public class AnswerFactory extends AbstractFactory {

    public Answer createOptionAnswer(List<String> answerList) {
        return new OptionsAnswer(answerList);
    }

    public Answer createTextAnswer(String answerText) {
        return new TextAnswer(answerText);
    }
}
