package ru.nikitin.server.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import ru.nikitin.server.entities.Stationery;
import ru.nikitin.server.services.impl.StationeryServiceImpl;

import javax.validation.Valid;

@Controller
@RequestMapping("/stationery")
class StationeryController {
    private final StationeryServiceImpl stationeryService;

    @Autowired
    public StationeryController(@Qualifier("stationeryServiceImpl") StationeryServiceImpl stationeryService) {
        this.stationeryService = stationeryService;
    }

    @GetMapping("/home")
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
        return "redirect:/stationery/home";
    }

    @GetMapping("/edit")
    public String editPage(Model model) {
        model.addAttribute("stationery", new Stationery());
        return "edit";
    }

    @PutMapping("/edit")
    public String editFormHandler(
            @ModelAttribute @Valid Stationery stationery,
            BindingResult bindingResult,
            @RequestParam("id") Integer id) {
        System.out.println(bindingResult);
        if (bindingResult.hasErrors())
            return "redirect:/stationery/edit";

        stationeryService.update(id, stationery);
        return "redirect:/stationery/home";
    }

    @GetMapping("/delete")
    public String deletePage() {
        return "delete";
    }

    @DeleteMapping("/delete")
    public String deleteFormHandler( @RequestParam("id") Integer id ) {
        stationeryService.delete(id);
        return "redirect:/stationery/home";
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
