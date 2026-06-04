import { Pane } from 'tweakpane';

export const PARAMS1 = {
  rotX: 0.5,
  rotY: 0.5,
  zoom: 5.0,
  autoRotate: true
};
export const PARAMS2 = {
  a: 2.0,
  b: 1.0,
  c: 1.0,
  h: 5.0,
  n: 50
};
export const PARAMS3 = {
  color1: { r: 255, g: 255, b: 0 },
  color2: { r: 0, g: 255, b: 255 }
};
export const PARAMS_LIGHT = {
  lightX: 2.0,
  lightY: 3.0,
  lightZ: 2.0,
  ambient: 0.3
};

const pane1 = new Pane({ title: 'Настройки Вида' });
pane1.addBinding(PARAMS1, 'rotX', { min: -Math.PI, max: Math.PI, step: 0.1, label: 'X' });
pane1.addBinding(PARAMS1, 'rotY', { min: -Math.PI, max: Math.PI, step: 0.1, label: 'Y' });
pane1.addBinding(PARAMS1, 'zoom', { min: 0.1, max: 100.0, step: 0.1, label: 'Zoom' });
pane1.addBinding(PARAMS1, 'autoRotate', { label: 'Auto-rotate' });
const btn = pane1.addButton({ title: 'Сбросить позицию' });
btn.on('click', () => {
  PARAMS1.rotX = 0.5;
  PARAMS1.rotY = 0.5;
  PARAMS1.zoom = 5.0;
  PARAMS1.autoRotate = false;
  pane1.refresh();
});

const pane2 = new Pane({ title: 'Настройки Формулы' });
pane2.addBinding(PARAMS2, 'a', { min: -5.0, max: 5.0, step: 0.05, label: 'A' });
pane2.addBinding(PARAMS2, 'b', { min: -5.0, max: 5.0, step: 0.05, label: 'B' });
pane2.addBinding(PARAMS2, 'c', { min: -5.0, max: 5.0, step: 0.05, label: 'C' });
pane2.addBinding(PARAMS2, 'h', { min: -5.0, max: 5.0, step: 0.05, label: 'H' });
pane2.addBinding(PARAMS2, 'n', { min: 10, max: 150, step: 1, label: 'Сегментов' });

const pane3 = new Pane({ title: 'Цвета поверхности' });
pane3.addBinding(PARAMS3, 'color1', { label: 'Цвет 1 (низ)', color: { type: 'int' } });
pane3.addBinding(PARAMS3, 'color2', { label: 'Цвет 2 (верх)', color: { type: 'int' } });

const pane4 = new Pane({ title: 'Настройки Лампочки' });
pane4.addBinding(PARAMS_LIGHT, 'lightX', { min: -10.0, max: 10.0, step: 0.1, label: 'Позиция X' });
pane4.addBinding(PARAMS_LIGHT, 'lightY', { min: -10.0, max: 10.0, step: 0.1, label: 'Позиция Y' });
pane4.addBinding(PARAMS_LIGHT, 'lightZ', { min: -10.0, max: 10.0, step: 0.1, label: 'Позиция Z' });
pane4.addBinding(PARAMS_LIGHT, 'ambient', { min: 0.0, max: 1.0, step: 0.05, label: 'Фоновый свет' });

pane2.element.style.top = '280px';
pane3.element.style.top = '500px';
pane4.element.style.top = '680px';

export { pane1, pane2, pane3, pane4 };