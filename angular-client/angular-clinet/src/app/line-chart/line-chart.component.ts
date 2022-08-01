import { Component, OnInit, ViewChild } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';

import {
  ChartComponent,
  ApexAxisChartSeries,
  ApexChart,
  ApexXAxis,
  ApexDataLabels,
  ApexTitleSubtitle,
  ApexStroke,
  ApexGrid,
} from 'ng-apexcharts';
import { SensorDataService } from '../sensor-data.service';

export type ChartOptions = {
  series: ApexAxisChartSeries;
  chart: ApexChart;
  xaxis: ApexXAxis;
  dataLabels: ApexDataLabels;
  grid: ApexGrid;
  stroke: ApexStroke;
  title: ApexTitleSubtitle;
};

@Component({
  selector: 'app-line-chart',
  templateUrl: './line-chart.component.html',
  styleUrls: ['./line-chart.component.css'],
})
export class LineChartComponent implements OnInit {
  @ViewChild('chart', { static: false }) chart!: ChartComponent;
  public chartOptions: ChartOptions;

  name: string = 'ph';

  addData() {
    setTimeout(() => {
      this.getData();
    }, 5);
    this.chartOptions.series = [
      {
        data: this.yAxis,
      },
    ];
    this.chartOptions.xaxis = {
      categories: this.xAxis,
    };
  }

  getData() {
    this.name = this.route.snapshot.params['name'];
    this.yAxis = [];
    this.xAxis = [];
    console.log(this.name);

    this.sensorService.getData().subscribe((enteringData) =>
      enteringData.forEach((sensorData) => {
        this.xAxis.push(sensorData.timeOfCheck);
        if (this.name === 'enviroment-temperture') {
          this.yAxis.push(sensorData.environmentTemperature);
        }
        if (this.name === 'liquid-temperture') {
          this.yAxis.push(sensorData.liquidTemperature);
        }
        if (this.name === 'tds') {
          this.yAxis.push(sensorData.tds);
        }
        if (this.name === 'co') {
          this.yAxis.push(sensorData.co2);
        }
        if (this.name === 'ph') {
          this.yAxis.push(sensorData.ph);
        }
      })
    );
    console.log(this.yAxis);
  }

  xAxis: Date[] = [];
  yAxis: number[] = [];

  ngOnInit(): void {
    this.yAxis = [];
    this.xAxis = [];
    this.sensorService.getData().subscribe((enteringData) =>
      enteringData.forEach((sensorData) => {
        this.xAxis.push(sensorData.timeOfCheck);
        if (this.name === 'enviroment-temperture') {
          this.yAxis.push(sensorData.environmentTemperature);
        }
        if (this.name === 'liquid-temperture') {
          this.yAxis.push(sensorData.liquidTemperature);
        }
        if (this.name === 'tds') {
          this.yAxis.push(sensorData.tds);
        }
        if (this.name === 'co') {
          this.yAxis.push(sensorData.co2);
        }
        if (this.name === 'ph') {
          this.yAxis.push(sensorData.ph);
        }
      })
    );
    this.addData();
  }

  constructor(
    private sensorService: SensorDataService,
    private route: ActivatedRoute
  ) {
    this.name = this.route.snapshot.params['name'];
    this.route.params.subscribe((params: Params) => {
      this.name = params['name'];
    });

    this.chartOptions = {
      series: [
        {
          name: 'Показатели с прибора',
          data: [0],
        },
      ],
      chart: {
        height: 500,
        type: 'line',
        zoom: {
          enabled: false,
        },
      },
      dataLabels: {
        enabled: true,
      },
      stroke: {
        curve: 'straight',
      },
      title: {
        text: 'Показатели с прибора',
        align: 'left',
      },
      grid: {
        row: {
          colors: ['#f3f3f3', 'transparent'], // takes an array which will be repeated on columns
          opacity: 0.5,
        },
      },
      xaxis: {
        categories: [],
      },
    };
  }
}
