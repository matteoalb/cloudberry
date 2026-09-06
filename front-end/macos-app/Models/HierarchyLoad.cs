using System.IO;
using System;
using System.Linq;
using System.Collections.Generic;

namespace macos_app.Models;

public static class HierarchyLoad
{
    private static string rootName = "cloudberry_tests";
    public static string pathToRoot = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Downloads");

    public static HierarchyElement Load()
    {
        // Temporary loading from local folder, replace when working with Raspberry Pi 5
        return LoadFromLocalFolder();
    }

    public static HierarchyElement LoadFromLocalFolder()
    {
        return LoadFromPath("", rootName, 0);
    }

    public static HierarchyElement LoadFromPath(string parentPath, string elemName, int depth)
    {
        Type type = GetTypeByName(elemName);
        string elemPath = Path.Combine(parentPath, elemName);
        HierarchyElement elem = new HierarchyElement(elemName, depth, elemPath);

        if(type != Type.Folder)
            return elem; // If it is not a folder, HierarchyElement directly is ready

        List<string> children = Directory.GetFileSystemEntries(Path.Combine(pathToRoot, elemPath))
                                .Select(Path.GetFileName)
                                .OfType<string>()
                                .ToList();

        foreach (string child in children)
        {
            elem.AddChild(LoadFromPath(elemPath, child, depth+1));
        }

        return elem;
    }

    public static Type GetTypeByName(string n)
    {
        if(!n.Contains('.'))
            return Type.Folder;

        if(n.Contains(".png") || n.Contains(".jpeg") || n.Contains(".jpg"))
            return Type.Image;

        return Type.Other;
    }
}