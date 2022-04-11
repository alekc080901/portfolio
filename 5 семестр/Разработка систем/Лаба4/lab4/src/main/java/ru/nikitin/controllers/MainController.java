package ru.nikitin.controllers;

import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import ru.nikitin.entities.Stationery;
import ru.nikitin.services.impl.StationeryServiceImpl;

import javax.validation.Valid;

@Controller
public @Data
class MainController {
    private final ApplicationContext context;
    private final StationeryServiceImpl stationeryService;

    @Autowired
    public MainController(ApplicationContext applicationContext) {
        this.context = applicationContext;
        this.stationeryService = context.getBean("stationeryServiceImpl", StationeryServiceImpl.class);
    }

    @GetMapping("/")
    public String mainPage(Model model) {
        model.addAttribute("stationery", stationeryService.getAll());
        return "home";
    }

    @GetMapping("/add")
    public String addPage(Model model) {
        model.addAttribute("stationery", new Stationery());
        return "add";
    }
    @PostMapping("/add")
    public String addFormHandler(@ModelAttribute("stationery") Stationery stationery) {
        stationeryService.add(stationery);
        return "redirect:/";
    }

    @GetMapping("/edit")
    public String editPage(Model model) {
        model.addAttribute("stationery", new Stationery());
        return "edit";
    }
    @PostMapping("/edit")
    public String editFormHandler(
            @ModelAttribute @Valid Stationery stationery,
            BindingResult bindingResult,
            @RequestParam("id") Integer id) {
        System.out.println(bindingResult);
        if (bindingResult.hasErrors())
            return "redirect:/edit";

        stationeryService.update(id, stationery);
        return "redirect:/";
    }

    @GetMapping("/delete")
    public String deletePage() {
        return "delete";
    }
    @PostMapping("/delete")
    public String deleteFormHandler( @RequestParam("id") Integer id ) {
        stationeryService.delete(id);
        return "redirect:/";
    }

    @GetMapping("/show_criteria")
    public String criteriaPage() {
        return "criteria";
    }
    @PostMapping("/show_criteria")
    public String criteriaFormHandler( @RequestParam String manufacturer, ModelMap model ) {
        model.addAttribute("stationery", stationeryService.getByManufacturer(manufacturer));
        return "criteria_result";
    }
}
