package net.pcae.pcaebackend.controller;

import net.pcae.pcaebackend.dto.CollectDto;
import net.pcae.pcaebackend.model.EntryModel;
import net.pcae.pcaebackend.repository.EntryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("collect")
public class CollectController {

    @Autowired
    private EntryRepository entryRepository;

    @GetMapping("test")
    public String getTest() {
        return "you are here";
    }

    @PostMapping("new")
    public ResponseEntity<String> postNew(@RequestBody CollectDto collectDto) {

        EntryModel entry = new EntryModel();
        entry.setLatitude(collectDto.latitude);
        entry.setLongitude(collectDto.longitude);
        entry.setTimestamp(collectDto.timestamp);
        entry.setCo_value(collectDto.co_value);

        entryRepository.save(entry);

        return new ResponseEntity<>("Collected new Data", HttpStatus.OK);
    }

}
