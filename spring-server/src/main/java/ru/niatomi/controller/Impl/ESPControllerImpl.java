package ru.niatomi.controller.Impl;

import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RestController;
import ru.niatomi.controller.ESPController;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;
import ru.niatomi.service.ESPService;

import java.util.List;

/**
 * @author niatomi
 */
@RestController
@AllArgsConstructor
public class ESPControllerImpl implements ESPController {

    private final ESPService espService ;

    @Override
    public ResponseEntity<ReferenceDataDto> getReferenceData() {
        return null;
    }

    @Override
    public ResponseEntity<List<TimeScheduleDto>> getTimeSchedule() {
        return null;
    }

    @Override
    public void saveSensorData(SensorsDto sensorsDto) {
        espService.saveSensorData(sensorsDto);
    }
}
