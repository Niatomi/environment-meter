import { HttpClient, HttpErrorResponse } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { catchError, Observable, throwError } from 'rxjs';

export interface SensorData {
  environmentTemperature: number;
  liquidTemperature: number;
  timeOfCheck: Date;
  tds: number;
  co2: number;
  ph: number;
}

@Injectable({
  providedIn: 'root',
})
export class SensorDataService {
  constructor(private http: HttpClient) {}
  baseURL = 'http://localhost:8080';

  getData(): Observable<SensorData[]> {
    return this.http
      .get<SensorData[]>(this.baseURL.concat('/client/getData'))
      .pipe(catchError(this.handleError));
  }

  private handleError(error: HttpErrorResponse) {
    if (error.status === 0) {
      // A client-side or network error occurred. Handle it accordingly.
      console.error('An error occurred:', error.error);
    } else {
      // The backend returned an unsuccessful response code.
      // The response body may contain clues as to what went wrong.
      console.error(
        `Backend returned code ${error.status}, body was: `,
        error.error
      );
    }
    // Return an observable with a user-facing error message.
    return throwError(() => new Error('Сервер не доступен. Попробуйте позже.'));
  }
}
