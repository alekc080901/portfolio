package com.company;

import java.util.List;
import java.util.StringJoiner;

public class OptionsAnswer extends Answer {
    private List<String> optionsText;

    public OptionsAnswer(List<String> optionsText) {
        this.optionsText = optionsText;
    }

    @Override
    public String toString() {
        StringJoiner sj = new StringJoiner(", ");
        optionsText.forEach(sj::add);
        return sj.toString();
    }

    public void setOptionsText(List<String> optionsText) {
        this.optionsText = optionsText;
    }
}
