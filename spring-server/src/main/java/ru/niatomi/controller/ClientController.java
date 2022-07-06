package ru.niatomi.controller;

import io.swagger.v3.oas.annotations.parameters.RequestBody;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.data.DataDto;
import ru.niatomi.model.dto.time.ExactTimeDto;
import ru.niatomi.model.dto.time.TimePlanAndExactDto;
import ru.niatomi.model.dto.time.TimePlanDto;

/**
 * @author niatomi
 */
@RestController
@RequestMapping("/client")
public interface ClientController {

    @PostMapping("/updateReference")
    public ResponseEntity<String> updateReferenceData(@RequestBody ReferenceData referenceData);

    @PostMapping("/addExactTime")
    public ResponseEntity<String> addExactTime(@RequestBody ExactTimeDto exactTimeDto);

    @PostMapping("/addTimePlan")
    public ResponseEntity<String> addTimePlan(@RequestBody TimePlanDto timePlanDto);

    @GetMapping("/getTimeSchedule")
    public ResponseEntity<TimePlanAndExactDto> getAllTime();

    @GetMapping("/getData")
    public ResponseEntity<DataDto> getData();


}
