namespace macos_app.Models;

using System;
using macos_app.ViewModels;
using macos_app.Views;

public class Hierarchy
{
    private readonly MainWindow window;

    private HierarchyElement root;

    public Hierarchy(MainWindow _window)
    {
        window = _window;
        root = HierarchyLoad.Load();

        PrintHierarchy();

        window.UpdateHierarchy(root);
    }

    public void PrintHierarchy()
    {
        Console.WriteLine(root.ToString());
    }
}