namespace macos_app.Models;

using System;
using System.Collections.Generic;
using macos_app.ViewModels;
using macos_app.Views;

public class Hierarchy
{
    private readonly MainWindow window;

    public HierarchyElement root;

    public Hierarchy(MainWindow _window)
    {
        window = _window;
        root = HierarchyLoad.Load();

        //PrintHierarchy();

        window.UpdateHierarchy(root);
    }

    public HierarchyElement GetElementByPath(string path)
    {
        string[] parts = path.Split('/', 2);
    
        if (parts.Length == 1)
            return root;

        return DFSPath(parts[1], root);
    }

    private static HierarchyElement DFSPath(string path, HierarchyElement parent)
    {
        string[] parts = path.Split('/', 2);
        HierarchyElement child = parent.GetChild(parts[0]);

        if (parts.Length == 1)
            return child;

        return DFSPath(parts[1], child);
    }

    public void PrintHierarchy()
    {
        Console.WriteLine(root.ToString());
    }
}