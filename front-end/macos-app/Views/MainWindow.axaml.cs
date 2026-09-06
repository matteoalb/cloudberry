using Avalonia.Controls;
using FluentAvalonia.UI.Controls;
using Avalonia;
using macos_app.Models;
using macos_app.ViewModels;
using System;

namespace macos_app.Views;

public partial class MainWindow : Window
{
    private Hierarchy hierarchy;

    public MainWindow()
    {
        InitializeComponent();

        hierarchy = new Hierarchy(this);
    }

    public void UpdateHierarchy(HierarchyElement root)
    {
        HierarchyStackPanel.Children.Clear();

        DisplayHierarchyElement(root);
    }

    private void DisplayHierarchyElement(HierarchyElement elem)
    {
        if(elem.name[0] == '.')
            return;

        var button = new Button
        {
            Content = "> " + elem.name,
            Margin = new Thickness(elem.depth * 16, 2, 0, 2)
        };

        button.Click += (s, e) => OnHierarchyElementClicked(elem.path);

        HierarchyStackPanel.Children.Add(button);

        if(elem.type != Models.Type.Folder)
            return;

        foreach (HierarchyElement child in elem.GetChildren())
        {
            DisplayHierarchyElement(child);
        }
    }

    private void OnHierarchyElementClicked(string path)
    {
        HierarchyElement element = hierarchy.GetElementByPath(path);

        if (DataContext is MainViewModel vm)
        {
            if (element == null || element.type == Models.Type.Folder)
            {
                vm.LoadFile("");
                return;
            }

            vm.LoadFile(path);
        }
    }
}