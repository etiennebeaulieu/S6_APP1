
#  Copyright (C) 2009,2011,2020. Max Hofheinz

import tkinter

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure

class Param(tkinter.Frame):
    def __init__(self, parent, callback, param_index, param_name):
        self.parent = parent
        self.param_index = param_index
        self.callback = callback
        tkinter.Frame.__init__(self, parent)
        self.label = tkinter.Label(self, text=param_name, width=25)
        self.label.pack(side=tkinter.LEFT)

    def on_value_change(self, adj):
        new_value = self.get_value()
        if self.last_value != new_value:
            self.last_value = new_value
            self.callback(self.param_index, new_value)

    def get_value(self):
        return self.last_value

    

class ParamFiddle(Param):
    def __init__(self, parent, callback, param_index, param_name, v_min, v_max, v_start=None, resolution=-1):
        Param.__init__(self, parent, callback, param_index, param_name)
        self.v_min = v_min
        self.v_max = v_max
        self.last_value = 0.5 * (v_min + v_max) if v_start is None else v_start
        self.scale = tkinter.Scale(self, from_=v_min, to=v_max, resolution=resolution, orient=tkinter.HORIZONTAL,
                                   showvalue=1,
                                   command=self.on_value_change)
        self.scale.set(self.last_value)
        self.scale.pack(side=tkinter.LEFT, expand=1, fill=tkinter.X)

    def get_value(self):
        return self.scale.get()



class ParamDropdown(Param):
    def __init__(self, parent, callback, param_index, param_name, entries_dict, default=None):
        Param.__init__(self, parent, callback, param_index, param_name)
        self.entries_dict = entries_dict
        if default is None or not default in entries_dict:
            default = list(entries_dict.keys())[0]
        self.last_value = entries_dict[default]
        self.selected_item = tkinter.StringVar()
        self.selected_item.set(default)
        self.menu = tkinter.OptionMenu(self, self.selected_item, *entries_dict.keys(), command = self.on_value_change)
        self.menu.pack(side=tkinter.LEFT, expand=1, fill=tkinter.X)

    def get_value(self):
        return self.entries_dict[self.selected_item.get()]
    
    


class FiddlePlotter(tkinter.Frame):
    def __init__(self, parent, plot_func, parameters, update_interval=False):
        tkinter.Frame.__init__(self, parent)
        self.parameters = parameters
        self.plot_func = plot_func
        color = None
        self.figure = Figure(figsize=(6, 4), linewidth=0, facecolor=color)
        self.canvas = FigureCanvasTkAgg(self.figure, master=self)
        self.canvas.get_tk_widget().pack(side=tkinter.TOP, fill=tkinter.BOTH, expand=1)
        self.paramControls = []
        for i, p in enumerate(parameters):
            if isinstance(p[1],dict):
                self.paramControls.append(ParamDropdown(self, self.on_param_control, i, *p))
            else:
                self.paramControls.append(ParamFiddle(self, self.on_param_control, i, *p))

        for p in self.paramControls:
            p.pack(side=tkinter.TOP, fill=tkinter.X)

        self.param_values = [p.get_value() for p in self.paramControls]
        toolbar = NavigationToolbar2Tk(self.canvas, self)
        toolbar.update()
        toolbar.pack(side=tkinter.TOP, fill=tkinter.X)
        self.update_interval = False
        self.update_plot(initial=True)
        self.updateID = None
        if update_interval:
            self.update_interval = int(update_interval * 1e3)
            self.updateID = self.after(self.update_interval, self.update_plot)

    def on_param_control(self, param_index, value):
        if self.updateID is not None:
            self.after_cancel(self.updateID)
            self.updateID = None
        self.param_values[param_index] = value
        self.update_plot()

    def update_plot(self, initial=False):
        self.plot_func(self.figure, *self.param_values, initial=initial)
        self.canvas.draw()
        if self.update_interval:
            self.updateID = self.after(self.update_interval, self.update_plot)




def fiddle(plot_func, parameters, update_interval = False):
    window = tkinter.Tk()
    window.geometry('800x800')
    window.title('FiddlePlotter')
    plotter = FiddlePlotter(window, plot_func, parameters, update_interval=update_interval)
    plotter.pack(expand=tkinter.YES, fill=tkinter.BOTH)
    window.mainloop()
