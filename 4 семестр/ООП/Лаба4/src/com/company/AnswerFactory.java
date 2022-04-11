package com.company;

import java.util.List;

public class AnswerFactory {
    Answer answer;

    public AnswerFactory(List<String> answerList) {
        this.answer = new OptionsAnswer(answerList);
    }

    public AnswerFactory(String answerText) {
        this.answer = new TextAnswer(answerText);
    }

    public Answer getAnswer() {
        return answer;
    }
}
