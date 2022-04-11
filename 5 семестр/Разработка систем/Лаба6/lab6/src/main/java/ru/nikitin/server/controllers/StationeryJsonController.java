package ru.nikitin.server.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ru.nikitin.server.entities.Stationery;
import ru.nikitin.server.services.impl.StationeryServiceImpl;

import java.util.List;

@Controller
@RequestMapping("/json/stationery")
public class StationeryJsonController {
    private final StationeryServiceImpl stationeryService;

    @Autowired
    public StationeryJsonController(@Qualifier("stationeryServiceImpl") StationeryServiceImpl stationeryService) {
        this.stationeryService = stationeryService;
    }

    @GetMapping(value = "/table", headers = {"Accept=application/json"})
    public @ResponseBody
    List<Stationery> jsonStationeryTable() {
        return stationeryService.getAll();
    }

    @ResponseBody
    @GetMapping(value="/table/{manufacturer}", headers = {"Accept=application/json"})
    public List<Stationery> getStationeryObject(@PathVariable("manufacturer") String manufacturer) {
        return stationeryService.getByManufacturer(manufacturer);
    }


    @PostMapping(value = "/table", headers = "Content-Type=application/json")
    @ResponseStatus(HttpStatus.NO_CONTENT)
    public void jsonAddPage(@RequestBody Stationery stationery) {
        stationeryService.add(stationery);
    }

    @PutMapping(value = "/table/{id}", headers = {"Accept=application/json"})
    public @ResponseBody
    void jsonEditPage(@PathVariable("id") int id, @RequestBody Stationery stationery) {
        stationeryService.update(id, stationery);
    }

    @DeleteMapping("/table/{id}")
    public @ResponseBody
    void jsonDeletePage(@PathVariable("id") int id) {
        stationeryService.delete(id);
    }
}
